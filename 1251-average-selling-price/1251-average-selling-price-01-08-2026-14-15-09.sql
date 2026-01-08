# Write your MySQL query statement below
SELECT Prices.product_id, ifnull(ROUND(SUM(price * units) / SUM(units), 2), 0) as 'average_price'
From Prices
         Left JOIN UnitsSold ON Prices.product_id = UnitsSold.product_id
    AND UnitsSold.purchase_date between Prices.start_date and Prices.end_date
GROUP BY Prices.product_id