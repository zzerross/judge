target := slv
sample := in1

all:
	for t in $(target); do \
		g++ -o $$t $$t.cpp; \
		mkdir -p log; \
		echo "$$t: "; \
		./$$t < $(sample) 2>&1 | tee log/$$t.$(sample); \
	done

smp:
	g++ -o smp smp.cpp
	./smp 2>&1 | tee in0

new:
	find ! -name Makefile | xargs rm -rf

cln:
	rm -rf log *.exe
