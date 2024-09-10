build:
	$$QBS build -f ./viewer/viewer.qbs --jobs 16 qbs.defaultBuildVariant:release qbs.installRoot:./installation -v

clear:
	rm -rf ./installation/*
	rm -rf ./default
	
install: build
	$$QBS install -f ./viewer/viewer.qbs qbs.defaultBuildVariant:"release" qbs.installRoot:./installation -v

run: install
	cd ./installation/usr/local/bin; ./runner.sh
