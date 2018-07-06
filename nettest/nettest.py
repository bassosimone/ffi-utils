# Types
# -----


class BooleanType(object):
    def __init__(self, value):
        self.value = bool(value)


class DoubleType(object):
    def __init__(self, value):
        self.value = float(value)


class LongType(object):
    def __init__(self, value):
        self.value = long(value)


class StringType(object):
    def __init__(self, value):
        self.value = bytes(value)


class MapStringStringType(object):
    def __init__(self):
        self.key = StringType("")
        self.value = StringType("")


class VectorStringType(object):
    def __init__(self):
        self.elem = StringType("")


# Model
# -----


class FailureASNLookupEvent(object):
    key = "failure.asn_lookup"
    failure = StringType("")


# ...


class StatusUpdatePerformanceEvent(object):
    key = "status.update_performance"
    direction = StringType("")
    elapsed = DoubleType(0.0)
    num_streams = LongType(0)
    speed_kbps = DoubleType(0.0)


class Options(object):
    bouncer_base_url = StringType("")
    dns_name_server = StringType("")
    ignore_bouncer_error = BooleanType(True)
    max_runtime = DoubleType(-1)

    @staticmethod
    def name_to_mkname(name):
        return {
            "dns_name_server": "dns/nameserver"
        }.get(name, name)


class Settings(object):
    annotations = MapStringStringType()
    disabled_events = VectorStringType()
    name = StringType("")
    options = Options()


class Nettest(object):
    events = (
        FailureASNLookupEvent(),
        StatusUpdatePerformanceEvent()
    )
