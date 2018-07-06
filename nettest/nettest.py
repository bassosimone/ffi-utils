# Types
# -----


class BooleanType(object):
    def __init__(self, value, doc=None):
        self.value = bool(value)
        self.__doc__ = doc


class DoubleType(object):
    def __init__(self, value, doc=None):
        self.value = float(value)
        self.__doc__ = doc


class LongType(object):
    def __init__(self, value, doc=None):
        self.value = long(value)
        self.__doc__ = doc


class StringType(object):
    def __init__(self, value, doc=None):
        self.value = bytes(value)
        self.__doc__ = doc


class MapStringStringType(object):
    def __init__(self, doc=None):
        self.key = StringType("")
        self.value = StringType("")
        self.__doc__ = doc


class VectorStringType(object):
    def __init__(self, doc=None):
        self.elem = StringType("")
        self.__doc__ = doc


# Model
# -----


class FailureASNLookupEvent(object):
    """ We could not lookup the ASN from the probe IP. """

    key = "failure.asn_lookup"

    failure = StringType("", doc="The actual failure that occurred.")


# ...


class StatusUpdatePerformanceEvent(object):
    """ Status update regarding measuring performance. """

    key = "status.update_performance"

    direction = StringType("", doc="Either 'download' or 'upload'.")

    elapsed = DoubleType(0.0, doc="Seconds elapsed since we started measuring.")

    num_streams = LongType(0, doc="Number of streams being used.")

    speed_kbps = DoubleType(0.0, doc="Speed measured in kbit/s.")


class Options(object):
    """ Scalar options controlling the behavior of a nettest. """

    bouncer_base_url = StringType("", doc="Base URL of the OONI bouncer")

    dns_name_server = StringType("", doc="Use this specific nameserver to resolve DNS names rather than using the default system resolver.")

    ignore_bouncer_error = BooleanType(True, doc="Ignore errors when contacting the OONI bouncer.")

    max_runtime = DoubleType(-1, doc="Maximum number of seconds for which nettests containing multiple inputs are allowed to run.")

    @staticmethod
    def name_to_mkname(name):
        return {
            "dns_name_server": "dns/nameserver"
        }.get(name, name)


class Settings(object):
    """ Contains all the settings of a network test. The most important, and the only mandatory field, is the network test `name`, that identifies what test to run. """

    annotations = MapStringStringType(
        doc="""Optional annotations that will be included into the report sent to the OONI collector.""")

    disabled_events = VectorStringType(
        doc="""List of events that will not be delivered becasue you do not care about them.""")

    name = StringType("", doc="Name of the test. This is a mandatory setting.")

    options = Options()


class Nettest(object):
    events = (
        FailureASNLookupEvent(),
        StatusUpdatePerformanceEvent()
    )
