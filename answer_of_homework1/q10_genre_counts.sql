With recursive split(genre, rest) as (
  select '', genres || ',' from titles where genres != "\N"
   union all
  select substr(rest, 0, instr(rest, ',')),
         substr(rest, instr(rest, ',')+1)
    from split
   where rest != ''
)
Select genre, count(*) as genre_count
  from split 
 where genre != ''
 group by genre
 order by genre_count desc;