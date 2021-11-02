SELECT T.type, primary_title, T.runtime_minutes 
FROM titles as T, (select type, max(runtime_minutes) as runtime_minutes from titles group by type) as rec 
WHERE T.runtime_minutes >= rec.runtime_minutes and T.type = rec.type 
ORDER BY T.type asc, primary_title asc;
