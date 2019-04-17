Shannon-Fano code
-----------------

A C++ program that, given a probability distribution
of symbols, generates the corresponding Shannon-Fano
code.

Compile with:

	mkdir build
	cd build
	cmake ..
	make

From inside `build`, run with:

	./shannon_fano ../test/alphabet

to generate the Shannon-Fano code fir the 26-letter
alphabet.

References
----------
[1] C. E. Shannon, *A mathematical theory of communication*. Bell system technical journal 27.3 (1948): 379-423.

[2] R. M. Fano, *The transmission of information*. Cambridge, Massachusetts Institute of Technology, Research Laboratory of Electronics, 1949.
