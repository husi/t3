BEGIN TRANSACTION;
CREATE TABLE projects (
    "Description" TEXT,
    "Id" INTEGER PRIMARY KEY,
    "Name" TEXT,
    "Parent" INTEGER
, "Deleted" INTEGER);
INSERT INTO "projects" VALUES('Example Project',1,'Example',NULL,NULL);
INSERT INTO "projects" VALUES('1st Example Subproject',2,'1st subproject',1,NULL);
INSERT INTO "projects" VALUES('2nd example subproject',3,'2nd subproject',1,NULL);
INSERT INTO "projects" VALUES('New Project',4,'New Project',NULL,NULL);
CREATE TABLE times (Comment TEXT, Duration TEXT, Start TEXT, Id INTEGER PRIMARY KEY, ProjectId NUMERIC);
INSERT INTO "times" VALUES(NULL,'00:01:27','2009-12-20T08:15:25',6,4);
INSERT INTO "times" VALUES(NULL,'00:02:00','2009-12-20T08:16:53',7,2);
INSERT INTO "times" VALUES(NULL,'00:01:34','2009-12-29T11:31:58',8,4);
INSERT INTO "times" VALUES(NULL,'00:00:22','2010-01-02T12:44:29',10,3);
COMMIT;
