FROM openjdk:11.0.3-jre-stretch
WORKDIR /hot
COPY shows shows
COPY config-mysql.json config.json
ENV HOT_VERSION 0.9.17-SNAPSHOT
RUN curl -sL https://github.com/dsolimando/Hot/releases/download/${HOT_VERSION}/hot-${HOT_VERSION}.tar.gz | tar xz
ENV HOT_HOME /hot/hot-${HOT_VERSION}
ENV PATH ${HOT_HOME}:${PATH}
CMD ["hot", "run"]
