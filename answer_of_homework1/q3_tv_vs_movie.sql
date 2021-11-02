Select type, count(*) as title_num 
From titles 
Group by type 
Order by title_num;