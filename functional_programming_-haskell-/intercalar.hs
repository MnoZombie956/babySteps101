intercalar [] lista = lista
intercalar lista [] = lista

intercalar (x1:resto1) (x2:resto2)
  | x1 > x2 = [x2]++intercalar (x1:resto1) (resto2)
  | x1 < x2 = [x1]++intercalar (resto1) (x2:resto2)
  | otherwise = [x1]++[x2]++intercalar (resto1) (resto2)
  
main = do
  let lista1 = [1,1,1,1,2,2,3,3,3,3,5,7,8,9,10]
  let lista2 = [1,1,1,2,7,8,9,20,25]
  print $ intercalar lista1 lista2 -- [1,1,1,1,1,1,1,2,2,2,3,3,3,3,5,7,7,8,8,9,9,10,20,25]
