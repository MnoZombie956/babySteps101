substituir _ _ [] = []
substituir a b (x:resto)
    | (x == a) = b:substituir a b resto
    | otherwise = x:substituir a b resto

main = do
    print(substituir 1 0 [1,2,1,3,1])

--[0,2,0,3,0]
