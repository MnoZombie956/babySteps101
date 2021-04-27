listaFatores n = [ x | x <- [1 .. n-1], n `mod` x == 0 ]
somaFatores [] = 0
somaFatores (x:resto) =
    x + (somaFatores resto)
perfeito :: Int -> Bool
perfeito n = n == somaFatores (listaFatores n)

main = do
    let n = 28
    print(perfeito n)
    print(listaFatores n)
    print(somaFatores (listaFatores n))

