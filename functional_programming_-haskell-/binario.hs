bin 0 = []--se nao entra em loop inf.
bin x =  (bin (x `div` 2)) ++ [x `mod` 2]
main = do
    let decToBin = 65164
    print(bin decToBin)