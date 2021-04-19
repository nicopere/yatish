PRAGMA foreign_keys = ON;
INSERT INTO yatish_client (name,sync) VALUES
  ('EduNat','I'),
  ('EIF','I');
INSERT INTO yatish_task (name,sync) VALUES
  ('Research','I'),
  ('Development','I'),
  ('Data','I'),
  ('Model','I'),
  ('Report','I'),
  ('Sysadmin','I'),
  ('Accounting','I'),
  ('Business','I'),
  ('maths-sciences','I'),
  ('planification','I'),
  ('évaluation','I'),
  ('coordination','I'),
  ('vie sco et conseils','I'),
  ('suivi stage','I'),
  ('(auto)formation','I');
INSERT INTO yatish_tool (name,sync) VALUES
  (' ','I'),
  ('Blender/Grass','I'),
  ('Basilisk/Gerris/Swat','I'),
  ('CodeBlocks/Poedit/HelpBlocks','I'),
  ('Drupal/Dokuwiki','I'),
  ('Windows','I'),
  ('Reporting-ERP','I'),
  ('bash/C/C++/SQL','I'),
  ('web/pdf/books','I'),
  ('bureautique/images','I'),
  ('tice/multimédia','I'),
  ('copies/cahiers','I'),
  ('papier-crayon','I'),
  ('photocop/papeterie','I'),
  ('chariot/labo','I'),
  ('tél.','I'),
  ('réunion-RdV','I'),
  ('courriel','I'),
  ('forums/réseaux','I'),
  ('Pronote','I'),
  ('SACoche','I'),
  ('Pyromaths','I'),
  ('GeoGebra','I');
INSERT INTO yatish_project (name,client_id,sync) VALUES
  ('DDL29',1,'I'),
  ('Portfolio',2,'I'),
  ('Yatish',2,'I');
INSERT INTO yatish_activity (project_id,task_id,tool_id,sync) VALUES
  (3,1,9,'I'),
  (3,2,8,'I');
/*INSERT INTO yatish_timeslot (start,activity_id,sync) VALUES (datetime('now'),1,'I');
UPDATE yatish_timeslot SET stop = datetime('now','+75 minutes') WHERE id = 1;
INSERT INTO yatish_timeslot (start,activity_id,sync) VALUES (datetime('now'),2,'I');
UPDATE yatish_timeslot SET stop = datetime('now','+125 minutes') WHERE id = 2;*/
/*INSERT INTO yatish_timeslot (start,stop,activity_id,sync) VALUES
  ('2020-02-19 09:30:00','2020-02-19 10:45:00',1,'I'),
  ('2020-02-19 11:15:00','2020-02-19 13:20:00',2,'I');
SELECT sum(round((strftime('%s',stop)-strftime('%s',start))/3600.,1))
  FROM yatish_timeslot GROUP BY activity_id;*/
/* Dans l'application, il est prévu que l'horodatage soit initié par sqlite
   puis seulement dupliqué dans mysql. La question du fuseau horaire est alors
   épineuse parce que le fuseau de l'application (sqlite) n'est pas forcément
   le même que celui du serveur (mysql).
   Première solution envisagée:
      sqlite: datetime('now','localtime')
      mysql: type TIMESTAMP
   => conversion de/vers UTC interne à mysql. Si les fuseaux serveur et application
   sont différents, ça fonctionnera du moment qu'on n'accède pas directement
   aux valeurs TIMESTAMP qui risquent d'être biaisées.
   Solution retenue:
      sqlite: datetime('now')
      mysql: type DATETIME
   => sqlite génère une horodate UTC et celle-ci n'est pas modifiée
   par le fuseau horaire du serveur mysql; si nécessaire c'est l'application
   qui sera chargée de convertir à la volée vers le fuseau horaire local. */
