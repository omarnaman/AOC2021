import System.IO

_splitOnChar :: String -> String -> Char -> (String, String)
_splitOnChar [] ys c = ([], ys) 
_splitOnChar (x:xs) ys c = if x == c then (xs, ys) else _splitOnChar xs (ys ++ [x]) c 
splitOnChar :: String -> Char -> (String, String)
splitOnChar xs = _splitOnChar xs []

_splitArrow :: String -> String -> (String, String)
_splitArrow xs ys = (fst $ splitOnChar (fst $ splitOnChar xs ' ') ' ', snd $ splitOnChar xs ' ')
splitArrow :: String -> (String, String)
splitArrow xs = _splitArrow xs []


parseCoordString :: (String, String) -> (Int, Int)
parseCoordString x = (read (snd x)::Int, read (fst x)::Int)

parseCoord :: String -> (Int, Int)
parseCoord coord = parseCoordString $ splitOnChar coord ','

parseLine line = (parseCoord $ snd $ splitArrow line, parseCoord $ fst $ splitArrow line)
parseLines = map parseLine

incrementElement list i = map (\x -> if snd x == i then fst x + 1 else fst x)  $ zip list [0..]

increment2DElement board i j = map (\x -> if snd x == j then incrementElement (fst x) i else fst x)  $ zip board [0..]

drawLine :: [[Int]] -> (Int, Int) -> (Int, Int) -> (Int, Int) -> [[Int]]
drawLine board cur end delta 
    | cur == end = uncurry (increment2DElement board) cur
    | otherwise = drawLine (uncurry (increment2DElement board) cur) (sumPairs cur delta) end delta

generateBoard :: [[Int]] -> Int -> Int -> [[Int]]
generateBoard board x y = if x == -1 then board else generateBoard (map (const 0) [0 .. y] : board) (x - 1) y

orgBoard :: [[Int]]
orgBoard = generateBoard [] 1000 1000 

isVertical :: ((Int, Int), (Int, Int)) -> Bool
isVertical line = fst (fst line) == fst (snd line) 

isHorizontal :: ((Int, Int), (Int, Int)) -> Bool
isHorizontal line = snd (fst line) == snd (snd line)

sumPairs :: (Int, Int) -> (Int, Int) -> (Int, Int)
sumPairs p1 p2 = (fst p1 + fst p2, snd p1 + snd p2)

getDelta :: ((Int, Int), (Int, Int)) -> (Int, Int)
getDelta line = (signum (fst (snd line) - fst (fst line)), signum (snd (snd line) - snd (fst line)))    

drawLines :: [[Int]] -> [((Int, Int),(Int, Int))] -> [[Int]]
drawLines board [] = board
drawLines board (line:lines) = drawLines (uncurry (drawLine board) line (getDelta line)) lines

isIntersecting x = if x > 1 then 1 else 0

countIntersecting :: [[Int]] -> Int
countIntersecting = foldr ((+) . foldr ((+) . isIntersecting) 0) 0

count :: [Integer] -> Integer 
count = foldr ((+) . isIntersecting) 0

count2D :: [[Integer]] -> Integer
count2D = foldr ((+) . count) 0


main :: IO()
main = do
    contents <- readFile "../test_input.in"
    putStrLn $ show $ countIntersecting $ drawLines orgBoard $ parseLines $ lines contents