Select primary_title, count(*) as nums 
From akas as a natural join titles 
Group by a.title_id 
Order by nums desc 
Limit 10;
