is_odd x = if x `rem` 2 /= 0 
   then True 
else False 

somaImpares [] = 0 -- lista vazia
somaImpares (x:lista) 
    | is_odd x = x + (somaImpares lista)
    | otherwise = somaImpares lista

main = do
    print(somaImpares [1,3,2,7,4,6,5])
