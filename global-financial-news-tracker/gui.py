# gui_pretty.py
import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QTableWidget, QTableWidgetItem,
    QHeaderView, QFrame
)
from PyQt5.QtGui import QColor, QFont
from PyQt5.QtCore import Qt
from aggregator import FinancialAggregator
from dotenv import load_dotenv
import os

load_dotenv()
STOCK_API_KEY = os.getenv("ALPHA_VANTAGE_API_KEY")
NEWS_API_KEY = os.getenv("NEWS_API_KEY")

aggregator = FinancialAggregator(STOCK_API_KEY, NEWS_API_KEY)

class FinancialApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("🌐 Global Financial News Tracker")
        self.setGeometry(100, 100, 900, 650)
        self.setStyleSheet("background-color: #f0f0f0;")

        self.layout = QVBoxLayout()
        self.layout.setContentsMargins(10, 10, 10, 10)  # smaller margins
        self.layout.setSpacing(10)  # less spacing
        self.setLayout(self.layout)
        input_layout = QHBoxLayout()

        self.symbol_input = QLineEdit()
        self.symbol_input.setPlaceholderText("Enter stock symbol (e.g., AAPL)")
        self.symbol_input.setFixedHeight(30)
        self.symbol_input.setStyleSheet("padding:5px; font-size:14px;")
        input_layout.addWidget(self.symbol_input)

        self.news_input = QLineEdit()
        self.news_input.setPlaceholderText("Enter news keyword (optional)")
        self.news_input.setFixedHeight(30)
        self.news_input.setStyleSheet("padding:5px; font-size:14px;")
        input_layout.addWidget(self.news_input)

        self.layout.addLayout(input_layout)
        btn_layout = QHBoxLayout()
        self.fetch_btn = QPushButton("Fetch Data")
        self.fetch_btn.setFixedHeight(30)
        self.fetch_btn.setStyleSheet(
            "background-color:#1976D2; color:white; font-weight:bold; padding:5px;"
        )
        self.fetch_btn.clicked.connect(self.fetch_data)
        btn_layout.addStretch()
        btn_layout.addWidget(self.fetch_btn)
        btn_layout.addStretch()
        self.layout.addLayout(btn_layout)
        self.stock_label = QLabel("")
        self.stock_label.setFont(QFont("Arial", 16, QFont.Bold))
        self.stock_label.setAlignment(Qt.AlignCenter)
        self.layout.addWidget(self.stock_label)
        line = QFrame()
        line.setFrameShape(QFrame.HLine)
        line.setFrameShadow(QFrame.Sunken)
        self.layout.addWidget(line)
        self.news_table = QTableWidget()
        self.news_table.setColumnCount(3)
        self.news_table.setHorizontalHeaderLabels(["Title", "Source", "Sentiment"])
        self.news_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.news_table.setAlternatingRowColors(True)
        self.news_table.setStyleSheet("""
            QTableWidget { background-color: white; gridline-color: #ddd; }
            QHeaderView::section { background-color: #1976D2; color: white; font-weight:bold; }
        """)
        self.layout.addWidget(self.news_table)

        self.summary_label = QLabel("")
        self.summary_label.setFont(QFont("Arial", 12))
        self.summary_label.setAlignment(Qt.AlignCenter)
        self.layout.addWidget(self.summary_label)

    def fetch_data(self):
        symbol = self.symbol_input.text().upper()
        news_query = self.news_input.text().strip() or None

        if not symbol:
            self.stock_label.setText("⚠ Please enter a stock symbol!")
            return

        try:
            insights = aggregator.get_company_insights(symbol, news_query)
        except Exception as e:
            self.stock_label.setText(f"Error: {e}")
            return

        stock = insights.get("stock_data")
        if "error" in stock:
            self.stock_label.setText(stock["error"])
        else:
            latest = stock["latest_close"]
            change = stock["price_change"]
            percent = stock["percent_change"]

            if change > 0:
                arrow, color = "▲", "green"
            elif change < 0:
                arrow, color = "▼", "red"
            else:
                arrow, color = "→", "orange"

            self.stock_label.setText(
                f"Latest Close: <b>{latest}</b> | "
                f"<span style='color:{color}; font-size:16px;'>Change: {arrow} {abs(change)} ({percent}%)</span>"
            )

        news = insights.get("news", [])
        self.news_table.setRowCount(len(news))

        positive_count = 0
        negative_count = 0
        neutral_count = 0

        for i, article in enumerate(news):
            title_item = QTableWidgetItem(article["title"])
            source_item = QTableWidgetItem(article["source"])
            sentiment_item = QTableWidgetItem(article["sentiment"])

            # Color sentiment
            if article["sentiment"] == "Positive":
                sentiment_item.setForeground(QColor("green"))
                positive_count += 1
            elif article["sentiment"] == "Negative":
                sentiment_item.setForeground(QColor("red"))
                negative_count += 1
            else:
                sentiment_item.setForeground(QColor("orange"))
                neutral_count += 1

            self.news_table.setItem(i, 0, title_item)
            self.news_table.setItem(i, 1, source_item)
            self.news_table.setItem(i, 2, sentiment_item)

        self.summary_label.setText(
            f"Positive: {positive_count} | Negative: {negative_count} | Neutral: {neutral_count}"
        )

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = FinancialApp()
    window.show()
    sys.exit(app.exec_())
