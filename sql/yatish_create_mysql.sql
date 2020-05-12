/*bash> mysql [--login-path=remote] ugl08693 <yatish_create_mysql.sql*/
CREATE TABLE yatish_client (
  id INT NOT NULL AUTO_INCREMENT,
  name VARCHAR (20) NOT NULL UNIQUE,
  PRIMARY KEY (id)
);
CREATE TABLE yatish_project (
  id INT NOT NULL AUTO_INCREMENT,
  name VARCHAR (20) NOT NULL UNIQUE,
  client_id INT NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (client_id) REFERENCES yatish_client (id)
    ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE yatish_task (
  id INT NOT NULL AUTO_INCREMENT,
  name VARCHAR (20) NOT NULL UNIQUE,
  PRIMARY KEY (id)
);
CREATE TABLE yatish_tool (
  id INT NOT NULL AUTO_INCREMENT,
  name VARCHAR (20) NOT NULL UNIQUE,
  PRIMARY KEY (id)
);
CREATE TABLE yatish_activity (
  id INT NOT NULL AUTO_INCREMENT,
  project_id INT NOT NULL,
  task_id INT NOT NULL,
  tool_id INT NOT NULL,
  PRIMARY KEY (id),
  UNIQUE (project_id,task_id,tool_id),
  FOREIGN KEY (project_id) REFERENCES yatish_project (id)
    ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (task_id) REFERENCES yatish_task (id)
    ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (tool_id) REFERENCES yatish_tool (id)
    ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE yatish_timeslot (
  id INT NOT NULL AUTO_INCREMENT,
  start DATETIME,
  stop DATETIME,
  activity_id INT NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (activity_id) REFERENCES yatish_activity (id)
    ON DELETE CASCADE ON UPDATE CASCADE
);
