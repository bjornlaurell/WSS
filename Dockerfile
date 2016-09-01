FROM scratch

COPY WSS_static_x86_Linux /

ENTRYPOINT ["/WSS_static_x86_Linux"]
