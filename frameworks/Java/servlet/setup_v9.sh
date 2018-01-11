#!/bin/bash

fw_depends java resin maven postgresql

mvn -P v9 clean compile war:war
rm -rf $RESIN_HOME/webapps/*
cp target/servlet.war $RESIN_HOME/webapps/
resinctl start
