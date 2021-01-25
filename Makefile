all:
	(cd src/mik && make)
	(cd src/mikgmp && make)

check:
	(cd src/mik && make check)
	(cd src/mikgmp && make check)

test:
	(cd src/mik && make test)
	(cd src/mikgmp && make test)

cleanup:
	(cd src/mik && make cleanup)
	(cd src/mikgmp && make cleanup)
