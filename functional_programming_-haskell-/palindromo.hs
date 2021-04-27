inverte [] = []
inverte (x:resto) = inverte resto ++ [x]

palindromo (x:resto) =
    [x]++resto == inverte ([x]++resto)

main = do
    let lista = [1,2,444,4,444,2,1] 
    print(palindromo lista)