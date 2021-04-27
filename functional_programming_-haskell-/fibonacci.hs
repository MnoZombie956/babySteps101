tamanho :: (Num b) => [a] -> b -- aproveitando uma funcao do primo.hs
tamanho [] = 0
tamanho (_:resto) = 1 + tamanho resto

inverte [] = [] -- aproveitando das questoes do tpIII
inverte (x:resto) = inverte resto ++ [x]

geraFibonacciUtil 0 = 0
geraFibonacciUtil 1 = 1
geraFibonacciUtil n = geraFibonacciUtil (n-1) + geraFibonacciUtil (n-2)

geraFibonacci tam
  | tam < 1 = []
  | otherwise = [geraFibonacciUtil (tam)] ++ geraFibonacci (tam-1)

comparaListas x y = x == y
comparaListas [] [] = True
comparaListas (x:xs) (y:ys)
  | x==y = comparaListas xs ys
  | x/=y = False
  
fibonacci [] = False
fibonacci [_] = False
fibonacci (x:xs) = comparaListas ([x]++xs) (inverte (geraFibonacci (tamanho ([x]++xs))))

main = do
  let lista = [1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181]
  print(inverte (geraFibonacci (tamanho (lista))))
  print(fibonacci lista)
