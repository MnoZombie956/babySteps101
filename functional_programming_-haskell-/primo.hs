tamanho :: (Num b) => [a] -> b
tamanho [] = 0
tamanho (_:resto) = 1 + tamanho resto

qntFatores :: Int -> Int
qntFatores n = tamanho [ x | x <- [2 .. n], n `mod` x == 0 ]

primo :: Int -> Bool
primo 0 = False
primo 1 = False
primo 2 = True
primo n = (qntFatores n) < 2 -- nenhum fator alem de ele mesmo, '1' nao conta
main = do
    let n =29
    print(primo n, qntFatores n, [ x | x <- [2 .. n], n `mod` x == 0 ])
