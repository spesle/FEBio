FROM intel/oneapi-hpckit:latest
SHELL ["/bin/bash", "-c"]

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install zip curl vim-common tmux -y

# Setup dependency installers
ARG DEPENDENCIES_PATH=/tmp/dependencies
RUN mkdir -p ${DEPENDENCIES_PATH}
COPY ./dependencies/ ${DEPENDENCIES_PATH}

RUN cd ${DEPENDENCIES_PATH} && \
    set -e; ${DEPENDENCIES_PATH}/install.sh \

WORKDIR /FEBio
CMD ["sleep", "infinity"]
