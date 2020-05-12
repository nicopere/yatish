/* Ces deux requêtes donnent le même résultat: */
SELECT name FROM yatish_project AS p
  WHERE p.id IN (SELECT project_id FROM yatish_activity);
SELECT DISTINCT name FROM yatish_project AS p
  INNER JOIN yatish_activity AS a ON a.project_id = p.id;
/* Tests pour l'IHM: */
SELECT p.name,t.name,t2.name FROM ((yatish_activity AS a
  INNER JOIN yatish_project AS p ON a.project_id = p.id)
  INNER JOIN yatish_task AS t ON a.task_id = t.id)
  INNER JOIN yatish_tool AS t2 ON a.tool_id = t2.id;
SELECT * FROM (((yatish_activity AS a
    INNER JOIN yatish_project AS p ON a.project_id = p.id)
    INNER JOIN yatish_task AS t ON a.task_id = t.id)
    INNER JOIN yatish_tool AS t2 ON a.tool_id = t2.id)
    INNER JOIN yatish_client AS c ON p.client_id = c.id
  WHERE p.name = 'Yatish'
    AND t.name = 'Research'
    AND t2.name LIKE '%SQL'
    AND c.name <> 'EduNat';
