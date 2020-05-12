/*bash> sqlite3 yatish.sqlite <yatish_create_sqlite.sql*/
CREATE TABLE yatish_client (
  id INTEGER, -- "INT" not auto-incremented!
  name TEXT NOT NULL UNIQUE,
  sync CHAR NOT NULL,
  PRIMARY KEY (id)
);
CREATE TABLE yatish_project (
  id INTEGER,
  name TEXT NOT NULL UNIQUE,
  client_id INT NOT NULL,
  sync CHAR NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (client_id) REFERENCES yatish_client (id)
    ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE TABLE yatish_task (
  id INTEGER,
  name TEXT NOT NULL UNIQUE,
  sync CHAR NOT NULL,
  PRIMARY KEY (id)
);
CREATE TABLE yatish_tool (
  id INTEGER,
  name TEXT NOT NULL UNIQUE,
  sync CHAR NOT NULL,
  PRIMARY KEY (id)
);
CREATE TABLE yatish_activity (
  id INTEGER,
  project_id INT NOT NULL,
  task_id INT NOT NULL,
  tool_id INT NOT NULL,
  sync CHAR NOT NULL,
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
  id INTEGER,
  start TEXT,
  stop TEXT,
  activity_id INT NOT NULL,
  sync CHAR NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (activity_id) REFERENCES yatish_activity (id)
    ON DELETE CASCADE ON UPDATE CASCADE
);
