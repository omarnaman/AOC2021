test: main.hs ../test_input.in
	ghc main.hs -o main -DTEST && ./main
real: main.hs ../real_input.in
	ghc main.hs -o main -DREAL && ./main
test_d: main.hs ../test_input.in
	ghc main.hs -o main -DTEST -DDEBUG && ./main
real_d: main.hs ../real_input.in
	ghc main.hs -o main -DREAL -DDEBUG && ./main