# clients/stock_client.py
from clients.abstract_client import AbstractDataClient

class StockClient(AbstractDataClient):
    def __init__(self, api_key: str):
        super().__init__(
            api_key=api_key,
            base_url="https://www.alphavantage.co/query"
        )

    def fetch_data(self, symbol: str):
        params = {
            "function": "TIME_SERIES_DAILY",
            "symbol": symbol,
            "apikey": self.api_key
        }
        return self.get(params)

    def transform_data(self, raw_data):
        time_series = raw_data.get("Time Series (Daily)", {})

        if not time_series:
            return None

        dates = list(time_series.keys())
        latest_day = dates[0]
        previous_day = dates[1]

        latest_close = float(time_series[latest_day]["4. close"])
        previous_close = float(time_series[previous_day]["4. close"])

        change = latest_close - previous_close
        percent_change = (change / previous_close) * 100

        return {
            "latest_date": latest_day,
            "latest_close": latest_close,
            "price_change": round(change, 2),
            "percent_change": round(percent_change, 2)
        }
