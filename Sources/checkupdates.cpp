/* --------------------------------------------
 * Originally created by,Thusitha Manathunga, 2012
 * Faculty of Engineering, University of Ruhuna.
 * ############################################
 * This was originally built on Qt 4.8.2
 * ============================================
 * A work of Serandibsoft, Sri Lanka
 * ############################################
 */

#include "checkupdates.h"

checkUpdates::checkUpdates(QObject *parent) :
    QObject(parent)
{

}
void checkUpdates::getParent(QWidget *parent)
{
    widget = new QWidget;
    widget = parent;
}

void checkUpdates::doCheck()
{
    // FIXME: Port to non-deprecated methods
    /*
    http = new QHttp(this);

    connect(http ,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));
    connect(http,SIGNAL(responseHeaderReceived(QHttpResponseHeader)),
            this,SLOT(responseHeaderReceived(QHttpResponseHeader)));
    connect(http,SIGNAL(requestFinished(int,bool)),this,SLOT(requestFinished(int,bool)));

    http->setHost("www.serandibsoft.com");
    http->get("/uploads/8/3/5/2/8352420/cute_editor.xml");
    */
}

void checkUpdates::stateChanged ( int state )
{
    switch(state)
    {
    case 0:
                qDebug() << "Unconnected...";
                break;
    case 1:
                qDebug() << "HostLookup...";
                break;
    case 2:
                qDebug() << "Connecting...";
                break;
    case 3:
                qDebug() << "Sending...";
                break;
    case 4:
                qDebug() << "Reading...";
                break;
    case 5:
                qDebug() << "Connected...";
                break;
    case 6:
                qDebug() << "Closing...";
                break;
    }
}

// FIXME: Port to non-deprecated methods
/*
void checkUpdates::responseHeaderReceived ( const QHttpResponseHeader & resp )
{
    qDebug() << "Size : " << resp.contentLength();
    qDebug() << "Type : " << resp.contentType();
    qDebug() << "State : " << resp.statusCode();

}
*/

void checkUpdates::requestFinished ( int id, bool error )
{
    // FIXME: Port to non-deprecated methods
    /*
    QString newVersion;
    QString features;
    QString link;

    if(error)
    {
        qDebug() << "Error Occured ...";
    }
    else
    {
        qDebug() << "OK...";
        QFile *file = new QFile(QDir::tempPath() + "/cute_editor.xml");
        if(file->open(QFile::Append))
        {
            file->write(http->readAll());
            file->flush();
            file->close();
        }
        QFile *xmlFile = new QFile(QDir::tempPath() + "/cute_editor.xml");
                  if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
                          qDebug() << "Error occured in xml File";
                  }
        QXmlStreamReader  *xmlReader = new QXmlStreamReader(xmlFile);
          //Parse the XML until we reach end of it
          while(!xmlReader->atEnd() && !xmlReader->hasError()) {
                  // Read next element
                  QXmlStreamReader::TokenType token = xmlReader->readNext();
                  //If token is just StartDocument - go to next
                  if(token == QXmlStreamReader::StartDocument) {
                          continue;
                  }
                  //If token is StartElement - read it
                  if(token == QXmlStreamReader::StartElement) {

                          if(xmlReader->name() == "cute_editor") {
                              continue;
                          }
                          if(xmlReader->name() == "version") {
                             newVersion =  xmlReader->readElementText();
                          }
                          if(xmlReader->name() == "features") {
                             features =  xmlReader->readElementText();

                          }
                          if(xmlReader->name() == "download_link") {
                             link  =  xmlReader->readElementText();
                          }
                  }
          }

          if(xmlReader->hasError()) {
                qDebug() << "Error occured in xmlReader";
         }
          //close reader and flush file
          xmlReader->clear();
          xmlFile->close();

          QSettings set(QSettings::IniFormat, QSettings::UserScope,
                                 "Serandibosft", "CutePad");
          if(newVersion.toFloat() > set.value("version",0.1).toFloat())
          {
              Updater mUpdater(widget);
              mUpdater.setModal(true);
              mUpdater.getInformation(set.value("version",0.1).toFloat(),
                                      newVersion.toFloat(),
                                      features,
                                      link);
              mUpdater.exec();
          }

         if(file->exists())
         {
          file->remove(QDir::tempPath() + "/cute_editor.xml");
         }
     }
    */
}


