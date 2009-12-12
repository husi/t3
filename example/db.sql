BEGIN TRANSACTION;
CREATE TABLE Projects (Description TEXT, Id INTEGER PRIMARY KEY, Name TEXT, Parent INTEGER);
INSERT INTO "Projects" VALUES('Example Project',1,'Example',NULL);
INSERT INTO "Projects" VALUES('1st Example Subproject',2,'1st subproject',1);
INSERT INTO "Projects" VALUES('2nd example subproject',3,'2nd subproject',1);
INSERT INTO "Projects" VALUES('New Project',4,'New Project',NULL);
COMMIT;
