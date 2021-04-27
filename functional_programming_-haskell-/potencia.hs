potencia :: Int -> Int -> Int 
potencia x y = do
    let y1 = y - 1
    if y>0 then
        x*potencia x y1
    else
        1
main = print(potencia 4 0)
