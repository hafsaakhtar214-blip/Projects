from abc import ABC, abstractmethod
import requests

class AbstractDataClient(ABC):

    def __init__(self, api_key: str, base_url: str):
        self.api_key = api_key
        self.base_url = base_url

    @abstractmethod
    def fetch_data(self, query: str):
        pass

    @abstractmethod
    def transform_data(self, raw_data):
        pass

    def get(self, params: dict):
        response = requests.get(self.base_url, params=params)
        response.raise_for_status()
        return response.json()
