FROM ubuntu:latest
RUN apt-get update && apt-get install -y mesa-utils
RUN apt-get install -y libglfw3-dev libgl1-mesa-dev libxrandr-dev \
                       libxinerama-dev libxcursor-dev libxi-dev

RUN mkdir src && mkdir src/shader
COPY src/shader/vertex_shader.glsl src/shader/
COPY src/shader/fragment_shader.glsl src/shader/

RUN mkdir img
COPY img/joachim-grüneis.256x256.jpg img/

ADD game .

CMD ["./game"]
