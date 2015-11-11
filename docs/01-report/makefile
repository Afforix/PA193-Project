all: pdf

pdf:
	for file in $$(ls *tex | cut -d \. -f 1) ; do make $$file.pdf ; done

%.pdf: %.tex *.bib
	latexmk $<

clean:
	rm -f *.toc *.aux *.log *.out *.bbl *.bcf *.blg *.dvi *.fls *.run.xml *.fdb_latexmk

mrproper:
	rm -f *.toc *.aux *.log *.out *.bbl *.bcf *.blg *.dvi *.fls *.run.xml *.fdb_latexmk *.pdf
