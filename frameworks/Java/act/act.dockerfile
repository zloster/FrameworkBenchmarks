FROM maven:3.6.1-jdk-11-slim as maven
WORKDIR /act
COPY pom.xml pom.xml
COPY src src
RUN mvn package -q

#TODO use separate JRE/JDK as the other builds
WORKDIR /act/target/dist
RUN tar xzf *.tar.gz
CMD ["java", "-server", "-Djava.security.egd=file:/dev/./urandom", "-Xms1G", "-Xmx1G", "-Xss320k", "-XX:+UseNUMA", "-XX:+UseParallelGC", "-XX:+AggressiveOpts", "-Dapp.mode=prod", "-Dapp.nodeGroup=", "-Dprofile=json_plaintext", "-Dxio.worker_threads.max=256", "-cp", "/act/target/dist/classes:/act/target/dist/lib/*", "com.techempower.act.AppEntry"]
