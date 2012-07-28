#ifndef GOOGLEDRIVESERVICE_H
#define GOOGLEDRIVESERVICE_H

#include "internetservice.h"

#include "core/network.h"
#include "core/tagreaderclient.h"

class QStandardItem;

class LibraryBackend;
class LibraryModel;
class QSortFilterProxyModel;

namespace google_drive {
  class Client;
  class ConnectResponse;
  class File;
  class ListFilesResponse;
}

class GoogleDriveService : public InternetService {
  Q_OBJECT
 public:
  GoogleDriveService(Application* app, InternetModel* parent);

  QStandardItem* CreateRootItem();
  void LazyPopulate(QStandardItem* item);

  QUrl GetStreamingUrlFromSongId(const QString& file_id);

 private slots:
  void ConnectFinished(google_drive::ConnectResponse* response);
  void FilesFound(const QList<google_drive::File>& files);
  void ListFilesFinished(google_drive::ListFilesResponse* response);
  void ReadTagsFinished(TagReaderClient::ReplyType* reply,
                        const google_drive::File& metadata,
                        const QString& url);

 private:
  void Connect();
  void RefreshAuthorisation(const QString& refresh_token);
  void MaybeAddFileToDatabase(const google_drive::File& file);

  QStandardItem* root_;

  google_drive::Client* client_;

  NetworkAccessManager network_;

  LibraryBackend* library_backend_;
  LibraryModel* library_model_;
  QSortFilterProxyModel* library_sort_model_;

  int indexing_task_id_;
};

#endif
