#!/bin/bash

sed -i 's|localhost|'"${DBHOST}"'|g' src/main/webapp/WEB-INF/resin-web.xml

fw_depends java resin maven postgresql

mvn -P v42 clean compile war:war
rm -rf $RESIN_HOME/webapps/*
cp target/servlet.war $RESIN_HOME/webapps/
resinctl start
