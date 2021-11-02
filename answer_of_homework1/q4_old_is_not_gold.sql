Select cast(premiered/10*10 as text)||'s' as decade, count(*) as p_num 
From titles 
Where premiered is not null 
Group by decade 
Order by p_num desc;