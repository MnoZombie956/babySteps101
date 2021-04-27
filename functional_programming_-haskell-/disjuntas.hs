qntTrues [] = 0
qntTrues (x:resto)--conta a quantidade de trues numa lista
    | x == True = 1 + qntTrues resto
    | x == False = qntTrues resto
    | otherwise = 0

arrIguais (x1:resto1) (x2:resto2) = -- caminha na lista1 e na lista2 criando um terceira lista com os booleans quando seus os elem se repetem na outra
    [x3==x4 | x3 <- ([x1]++resto1), x4 <- ([x2]++resto2)]

disjuntas (x1:resto1) (x2:resto2) =
    qntTrues (arrIguais (x1:resto1) (x2:resto2)) == 0--se mais que 1 elem repetido ent, nao eh disjunta

main = do
    let lista1 = [1,0,3,6] 
    let lista2 = [5,4,11,10,18,15,16]
    print(disjuntas lista1 lista2)
    print(arrIguais lista1 lista2)
