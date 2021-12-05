FROM intel/oneapi-basekit:devel-ubuntu18.04
SHELL ["/bin/bash", "-c"]

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install zip -y

# Setup dependency installers
ARG DEPENDENCIES_PATH=/tmp/dependencies
RUN mkdir -p ${DEPENDENCIES_PATH}
COPY ./dependencies/ ${DEPENDENCIES_PATH}

RUN set -e; ${DEPENDENCIES_PATH}/install.sh
WORKDIR /FEBio
CMD ["sleep", "infinity"]
