FROM python:3-alpine

RUN apk update && apk add curl

# set up the user
RUN addgroup ctfuser && adduser -G ctfuser -h /app -D ctfuser

# copy the files
COPY . /app
WORKDIR /app

# add file write access for images
RUN chown -R ctfuser:ctfuser /app
RUN chmod 755 /app/images

# install requirements
RUN pip3 install -r requirements.txt
USER ctfuser
CMD gunicorn --log-level debug -b 0.0.0.0:5000 app:app
