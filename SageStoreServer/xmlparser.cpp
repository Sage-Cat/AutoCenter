#include "xmlparser.h"

#include <QXmlStreamReader>

XmlParser::XmlParser(QObject *parent) :
    QObject(parent),
    lost_part("")
{

}

RecordsList* XmlParser::parseOmegaPriceList(const QString &xmlData)
{       
    // We devide xml-file into pieces, so we should prevent the loss of data
    QString data_to_parse = lost_part + xmlData;

    // Get new lost part
    int indexOfLastRecord = data_to_parse.lastIndexOf("<Прайс>");
    lost_part = "";
    if(indexOfLastRecord > data_to_parse.lastIndexOf("</Прайс>")) // if we do not have a close tag
    {
        lost_part = data_to_parse.mid(indexOfLastRecord);
        data_to_parse.remove(
                    indexOfLastRecord,
                    data_to_parse.length() - indexOfLastRecord
                    ); // erase the new lost_part to prevent mistakes
    }

    recordsList.clear();

    // ORDER ACCORDING TO DATABASE
    QString Code = "-",
            Catalog = "-",
            TNVED = "-",
            Name_Product = "-",
            Unit = "шт",
            Price = "0.0";

    // START PARSING
    QXmlStreamReader reader(data_to_parse);
    int miss_count = 0; // counter for errors
    while(reader.readNextStartElement() && miss_count < MAX_NUMBER_OF_MISSES)
    {
        if(reader.name() == "Прайс")
        {
            miss_count = 0;

            while(reader.readNextStartElement())
            {
                if(reader.name() == "KART")        Code            = reader.readElementText(); else
                if(reader.name() == "KODKAT")      Catalog         = reader.readElementText(); else
                if(reader.name() == "KODTNVED")    TNVED           = reader.readElementText(); else
                if(reader.name() == "NAIM")        Name_Product    = reader.readElementText(); else
                if(reader.name() == "NAIMUKR")     Name_Product    = reader.readElementText(); else
                if(reader.name() == "BAZED")       Unit            = reader.readElementText(); else
                if(reader.name() == "MINCENA")     Price           = reader.readElementText(); else reader.skipCurrentElement();
            }

            // PACK NEW RECORD
            if(Code != "-")
                recordsList.push_back({Code, Catalog, TNVED, Name_Product, Unit, Price});

            // SET DEFAULT TO CHECK FOR A FOOL
            // ex: user wants to load the pricelist with a similar start "Прайс", but with different keys
            // => here we get a bunch of default-records relentlessly flooding the database
            Code = "-";
        }
        else
            miss_count++;
    }

    return &recordsList;
}
