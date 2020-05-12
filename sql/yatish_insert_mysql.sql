INSERT INTO yatish_client (name) VALUES
  ('EduNat'),
  ('EIF');
INSERT INTO yatish_task (name) VALUES
  ('Research'),
  ('Development'),
  ('Accounting'),
  ('Data'),
  ('Model'),
  ('Report'),
  ('maths-sciences'),
  ('coordination'),
  ('vie sco et conseils'),
  ('examens, certifs'),
  ('(auto)formation');
INSERT INTO yatish_tool (name) VALUES
  ('blender/grass'),
  ('basilisk/gerris/swat'),
  ('drupal/dokuwiki'),
  ('SACoche'),
  ('bash/C/C++/SQL'),
  ('web/pdf/books'),
  ('bureautique-images'),
  ('courriel'),
  ('secrétariat'),
  ('tél.'),
  ('réunion-Rdv'),
  ('reporting-ERP'),
  ('forums/réseaux'),
  ('photocop/chariot'),
  ('correction copies'),
  ('TICE/multimédia');
INSERT INTO yatish_project (name,client_id) VALUES
  ('DDL29',1),
  ('Portfolio',2),
  ('Yatish',2);
INSERT INTO yatish_activity (project_id,task_id,tool_id) VALUES
  (3,1,6),
  (3,2,5);
INSERT INTO yatish_timeslot (start,stop,activity_id) VALUES
  ('2020-02-19 09:30:00','2020-02-19 10:45:00',1),
  ('2020-02-19 11:15:00','2020-02-19 13:20:00',2);
SELECT sum(round((unix_timestamp(stop)-unix_timestamp(start))/3600.,1))
  FROM yatish_timeslot GROUP BY activity_id;
