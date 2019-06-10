FROM alpine:3.8 as builder
RUN apk update && apk add gcc g++ sqlite-dev --no-cache
COPY main.cpp /main.cpp
RUN g++ /main.cpp -lsqlite3 -o main 

FROM alpine:3.8
COPY --from=builder /main /main
RUN apk add sqlite-dev  libstdc++ --no-cache
VOLUME /db
ENTRYPOINT ["/main"] 
