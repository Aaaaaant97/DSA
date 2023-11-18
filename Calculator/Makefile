#编译main.cpp文件规则
test: main.cpp input.txt
	g++ -o test main.cpp  

#编译report.tex文件产生report.pdf规则
report.pdf: report.tex  
	xelatex report.tex  

#清理规则
clean:  
	rm -f test report.pdf report.aux report.log  