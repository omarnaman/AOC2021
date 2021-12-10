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


splitListInHalf :: [t] -> ([t], [t])
splitListInHalf s = _splitListInHalf s []

parseCoordString :: (String, String) -> (Int, Int)
parseCoordString x = (read (snd x)::Int, read (fst x)::Int)

parseCoord :: String -> (Int, Int)
parseCoord coord = parseCoordString $ splitOnChar coord ','

parseLine line = (parseCoord $ snd $ splitArrow line, parseCoord $ fst $ splitArrow line)
parseLines = map parseLine

incrementElement list i = map (\x -> if snd x == i then fst x + 1 else fst x)  $ zip list [0..]

increment2DElement board i j = map (\x -> if snd x == j then incrementElement (fst x) i else fst x)  $ zip board [0..]

drawLineHor :: [[Int]] -> Int -> Int -> Int -> [[Int]]
-- drawLineHor board row begin end = if begin == end then board else drawLineHor (increment2DElement board row begin) row (begin + 1) end
drawLineHor board row begin end 
    | begin == end = increment2DElement board row begin
    | begin > end =  drawLineHor board row end begin
    | otherwise = drawLineHor (increment2DElement board row begin) row (begin + 1) end

drawLineVer :: [[Int]] -> Int -> Int -> Int -> [[Int]]
drawLineVer board col begin end 
    | begin == end = increment2DElement board begin col
    | begin > end = drawLineVer board col end begin
    | otherwise = drawLineVer (increment2DElement board begin col) col (begin + 1) end

drawLineDiagonal :: [[Int]] -> Int -> Int -> Int -> [[Int]]
-- drawLineDiagonal board col begin end 
--     | begin == end = increment2DElement board begin col
--     | begin > end = drawLineVer board col end begin
--     | otherwise = drawLineVer (increment2DElement board begin col) col (begin + 1) end

generateBoard :: [[Int]] -> Int -> Int -> [[Int]]
generateBoard board x y = if x == -1 then board else generateBoard (map (const 0) [0 .. y] : board) (x - 1) y

orgBoard :: [[Int]]
orgBoard = generateBoard [] 1000 1000 

isVertical :: ((Int, Int), (Int, Int)) -> Bool
isVertical line = fst (fst line) == fst (snd line) 

isHorizontal :: ((Int, Int), (Int, Int)) -> Bool
isHorizontal line = snd (fst line) == snd (snd line)

isDiagonalPos :: ((Int, Int), (Int, Int)) -> Bool
isDiagonalPos line = div (snd (fst line) - snd (snd line)) (fst (fst line) - fst (snd line)) == 1 

isDiagonalNeg :: ((Int, Int), (Int, Int)) -> Bool
isDiagonalNeg line = div (snd (fst line) - snd (snd line)) (fst (fst line) - fst (snd line)) == -1

drawLines :: [[Int]] -> [((Int, Int),(Int, Int))] -> [[Int]]
drawLines board [] = board  

drawLines board (line:lines) 
    | isHorizontal line = drawLines (drawLineHor board (snd $ fst line) (fst $ fst line) (fst $ snd line)) lines 
    | isVertical line = drawLines (uncurry (drawLineVer board) (fst line) (snd $ snd line)) lines 
    | otherwise =  drawLines board lines

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