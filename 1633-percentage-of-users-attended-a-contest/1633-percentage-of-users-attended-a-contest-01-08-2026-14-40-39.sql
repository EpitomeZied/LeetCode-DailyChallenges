# Write your MySQL query statement below
select contest_id, ROUND(COUNT(Register.user_id) / (SELECT COUNT(*) FROM Users) * 100 , 2) as percentage
from Register
         LEFT JOIN Users as u ON u.user_id = Register.user_id
GROUP BY contest_id
order by percentage desc  , contest_id;