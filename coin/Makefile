#编译main.cpp文件规则
main: main.cpp coin.h
	g++ -o main main.cpp

#编译report.tex文件产生report.pdf规则
report: report.tex
	xelatex report.tex  

#清理规则
clean:  
	rm -f main report.pdf report.aux report.log  
