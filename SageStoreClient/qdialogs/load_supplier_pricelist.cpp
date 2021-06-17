#include "load_supplier_pricelist.h"
#include "ui_load_supplier_pricelist.h"

#include <QFileDialog>
#include <QMessageBox>

#include "statements.h"

Load_supplier_pricelist::Load_supplier_pricelist(QWidget *parent, TcpClient *client) :
    QDialog(parent),
    ui(new Ui::Load_supplier_pricelist),
    client(client)
{
    ui->setupUi(this);

    ui->btn_stop->setDisabled(true);
}

Load_supplier_pricelist::~Load_supplier_pricelist()
{
    delete ui;
}

void Load_supplier_pricelist::on_btn_load_clicked()
{
    QString fileName = ui->line_path->text();
    if(fileName != "")
    {
        // FILE FOR READING
        file = new QFile(fileName);
        if(!file->open(QFile::ReadOnly | QFile::Text))
            QMessageBox::critical(this, "Помилка", "Не виходить відкрити файл", QMessageBox::Ok);

        // SUPPLIER DETECT
        int supplier_number = ui->comboBox->currentIndex();

        // THREAD
        thread = new QThread;

        // WORKER
        this->RAS = new ReaderAndSender(client, file, LIST_OF_SUPPLIERS.at(supplier_number));

        connect(thread, SIGNAL(started()), RAS, SLOT(doWork()));
        connect(RAS, SIGNAL(countChanged(int)), this, SLOT(updateProcessInfo(int)));
        connect(RAS, SIGNAL(errorDetected()), this, SLOT(handleError()));
        connect(RAS, SIGNAL(finished()), this, SLOT(finishWork()));
        connect(this, SIGNAL(abort()), RAS, SLOT(forceQuit()));
        connect(RAS, SIGNAL(sendData(const QString&)), client, SLOT(sendData(const QString&)));

        connect(RAS, SIGNAL(finished()), thread, SLOT(quit()));
        connect(RAS, SIGNAL(finished()), RAS, SLOT(deleteLater()));
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        RAS->moveToThread(thread);

        ui->btn_stop->setDisabled(false);
        ui->btn_load->setDisabled(true);
        thread->start();
    }
}


void Load_supplier_pricelist::on_btn_explorer_clicked()
{
    auto fileNames = QFileDialog::getOpenFileNames(this, "Завантажити з","/",tr("XML-файли (*.xml)"));
    if(!fileNames.empty())
        ui->line_path->setText(fileNames.at(0));
}

void Load_supplier_pricelist::updateProcessInfo(int count)
{
    int actual = count / 3; // 3 lines for record
    QString res = "Записів опрацьовано:  " + QString::number(actual);
    ui->label_status->setText(res);

    ui->progressBar->setValue(float(actual % PROGRESSBAR_DEVIDER) / float(PROGRESSBAR_DEVIDER) * 100);
}

void Load_supplier_pricelist::handleError()
{
    QMessageBox::critical(this, "Помилка", "Не виходить завантажити прайсліст. Звернися до програміста", QMessageBox::Ok);
}

void Load_supplier_pricelist::finishWork()
{
    ui->progressBar->setValue(100);

    ui->btn_stop->setDisabled(true);
    ui->btn_load->setDisabled(false);
}

ReaderAndSender::ReaderAndSender(TcpClient *client, QFile *file, QString supplier) :
    client(client),
    file(file),
    supplier(supplier),
    abort(false)
{
}

void ReaderAndSender::doWork()
{
    QTextStream in(file);
    int count = 0;
    QString xmlData = "";

    // client:::[UID]:::uniq:::addProductTypes:::[supplier]:::[2000 or less records]
    QStringList requestList{
        "uniq",
        "addProductTypes",
        supplier
    };

    while(!in.atEnd() && !abort)
    {
        xmlData += in.readLine();
        count++;

        if(count % 7 == 1) // random condition
            emit countChanged(count);

        if(count % COUNT_OF_XML_PRICELIST_LINES_TO_SEND == 0 || in.atEnd()) // lines or end of file
        {
            // SEND DATA
            if(client->send_and_get_response(requestList.join(DELIMITER_MAIN) + DELIMITER_MAIN + xmlData) == "0")
            {
                emit errorDetected();
                break;
            }

            // for the next iteration
            xmlData = "";
        }
    }
    emit finished();
}

void ReaderAndSender::forceQuit()
{
    abort = true;
    emit finished();
}

void Load_supplier_pricelist::on_btn_stop_clicked()
{
    emit abort();
}
