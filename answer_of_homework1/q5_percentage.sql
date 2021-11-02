Select 
Cast(premiered/10*10 as text) as decade, 
Round(count(*)*100.0/(select count(*) from titles), 4) as per 
From titles where premiered is not null 
Group by decade 
Order by per desc;