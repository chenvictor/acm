import logging, sys

class ShutdownHandler(logging.StreamHandler):
    def emit(self, record):
        sys.exit(1)

def make_logger(verbose_level):
    logger = logging.getLogger(__name__)
    formatter = logging.Formatter('[%(levelname)s] %(message)s')

    handler = logging.StreamHandler()
    handler.setLevel(logging.DEBUG)
    handler.setFormatter(formatter)

    # exits when after error log printed
    shutdown = ShutdownHandler()
    shutdown.setLevel(logging.ERROR)

    logger.addHandler(handler)
    logger.addHandler(shutdown)

    if verbose_level > 0:
        logger.setLevel(logging.DEBUG)
    else:
        logger.setLevel(logging.INFO)

    return logger

