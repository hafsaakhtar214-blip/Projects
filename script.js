let allProducts = [];
let currentUser = null;
let selectedCategory = null;
window.lastBackendDiscount = 0;

function getLoggedInUser() {
    return JSON.parse(localStorage.getItem("loggedInUser"));
}

function setLoggedInUser(user) {
    if (user.phone) delete user.phone;
    localStorage.setItem("loggedInUser", JSON.stringify(user));
    currentUser = user;
    updateHeaderUser();
}

function logoutUser() {
    localStorage.removeItem("loggedInUser");
    currentUser = null;
    updateHeaderUser();
}

function updateHeaderUser() {
    const loginIcon = document.getElementById("loginIcon");
    const userMenu = document.getElementById("userMenu");
    const userNameElem = document.getElementById("userName");
    const logoutBtn = document.getElementById("logoutBtn");
    const dropdownMenu = document.getElementById("userDropdown");

    const user = getLoggedInUser();

    if (user) {
        currentUser = user;
        if (loginIcon) loginIcon.style.display = "none";
        if (userMenu) userMenu.style.display = "flex";
        if (userNameElem) userNameElem.innerText = user.name;
        if (logoutBtn) logoutBtn.onclick = logoutUser;
    } else {
        if (loginIcon) loginIcon.style.display = "inline-flex";
        if (userMenu) userMenu.style.display = "none";
        if (userNameElem) userNameElem.innerText = "";
    }

    if (userNameElem && dropdownMenu) {
        userNameElem.onclick = (e) => {
            e.stopPropagation();
            dropdownMenu.classList.toggle("show");
        };
        document.addEventListener("click", (e) => {
            if (!userMenu.contains(e.target)) {
                dropdownMenu.classList.remove("show");
            }
        });
    }
}

// ===================== SIGNUP/LOGIN FORMS =====================
const signupForm = document.getElementById("signupForm");
if (signupForm) {
    signupForm.addEventListener("submit", async (e) => {
        e.preventDefault();
        const name = document.getElementById("name").value;
        const email = document.getElementById("email").value;
        const password = document.getElementById("password").value;

        try {
            const res = await fetch("http://127.0.0.1:8000/api/signup", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ name, email, password })
            });
            const data = await res.json();
            if (!res.ok) throw new Error(data.detail || "Signup failed");
            setLoggedInUser(data.user);
            alert(`Welcome, ${data.user.name}!`);
            window.location.href = "index.html";
        } catch (err) {
            alert(err.message);
        }
    });
}

const loginForm = document.getElementById("loginForm");
if (loginForm) {
    loginForm.addEventListener("submit", async (e) => {
        e.preventDefault();
        const email = document.getElementById("email").value;
        const password = document.getElementById("password").value;

        try {
            const res = await fetch("http://127.0.0.1:8000/api/login", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ email, password })
            });
            const data = await res.json();
            if (!res.ok) throw new Error(data.detail || "Login failed");
            setLoggedInUser(data.user);
            alert(`Welcome back, ${data.user.name}!`);
            window.location.href = "index.html";
        } catch (err) {
            alert(err.message);
        }
    });
}

// ===================== CART FUNCTIONS =====================
function getCart() {
    return JSON.parse(localStorage.getItem("cart")) || [];
}

function saveCart(cart) {
    localStorage.setItem("cart", JSON.stringify(cart));
    updateCartCount();
    renderCart();
    showRecommendationsAI();
}

function updateCartCount() {
    const cart = getCart();
    const count = cart.reduce((sum, i) => sum + i.quantity, 0);
    const badge = document.querySelector(".cart-count");
    if (badge) badge.innerText = count;
}

function addToCart(product) {
    let cart = getCart();
    const existing = cart.find(p => p.ProductID === product.ProductID);
    if (existing) existing.quantity++;
    else cart.push({ ProductID: product.ProductID, quantity: 1 });
    saveCart(cart);
}

// ===================== LOAD PRODUCTS =====================
fetch("products.json")
    .then(res => res.json())
    .then(data => {
        allProducts = data;
        initPage();
    })
    .catch(err => console.error("Product JSON Error:", err));

function initPage() {
    currentUser = getLoggedInUser();
    updateCartCount();
    readCategoryFromURL();

    if (document.getElementById("productsGrid")) {
        renderCollection();
        setupSearchListener();
    }
    if (document.getElementById("cartContainer")) renderCart();
    if (document.getElementById("checkoutForm")) prefillCheckoutForm();
    if (document.getElementById("productImage")) loadProductPage();
}

function readCategoryFromURL() {
    const params = new URLSearchParams(window.location.search);
    selectedCategory = params.get("category");
}

function setupSearchListener() {
    const searchInput = document.getElementById("searchInput");
    if (!searchInput) return;

    searchInput.addEventListener("input", () => {
        renderCollection();
    });
}

// ===================== RENDER PRODUCTS =====================
function renderCollection() {
    const grid = document.getElementById("productsGrid");
    if (!grid) return;

    const searchInput = document.getElementById("searchInput");
    const noProducts = document.getElementById("noProducts");

    let filtered = [...allProducts];
    if (selectedCategory) filtered = filtered.filter(p => p.Category === selectedCategory);
    if (searchInput && searchInput.value.trim() !== "") {
        const q = searchInput.value.toLowerCase();
        filtered = filtered.filter(p => p.ProductName.toLowerCase().includes(q));
    }

    grid.innerHTML = "";
    if (filtered.length === 0) {
        if (noProducts) noProducts.style.display = "block";
        return;
    }
    if (noProducts) noProducts.style.display = "none";

    filtered.forEach(p => {
        const card = document.createElement("div");
        card.className = "product-card";
        card.innerHTML = `
            <img src="Pictures/${p.Image}" class="product-img">
            <div class="product-info">
                <div class="product-name">${p.ProductName}</div>
                <div class="product-weight">${p.Weight || ""}</div>
                <div class="product-price">Rs. ${p.Price}</div>
                <button class="add-to-cart btn">Add to Cart</button>
            </div>
        `;
        card.querySelector(".add-to-cart").onclick = (e) => { e.stopPropagation(); addToCart(p); };
        card.onclick = () => { window.location.href = `product.html?id=${p.ProductID}`; };
        grid.appendChild(card);
    });
}

// ===================== PRODUCT PAGE =====================
function loadProductPage() {
    const params = new URLSearchParams(window.location.search);
    const productId = params.get("id");
    const product = allProducts.find(p => String(p.ProductID) === String(productId));
    if (!product) return;

    document.getElementById("productImage").src = `Pictures/${product.Image}`;
    document.getElementById("productName").innerText = product.ProductName;
    document.getElementById("productWeight").innerText = product.Weight || "";
    document.getElementById("productPrice").innerText = `Rs. ${product.Price}`;

    const addBtn = document.getElementById("addToCartBtn");
    if (addBtn) addBtn.onclick = () => addToCart(product);

    showRecommendationsAI();
}

async function showRecommendationsAI() {
    const container = document.getElementById("recommendations");
    const user = getLoggedInUser();
    if (!container || allProducts.length === 0) return;

    const cart = getCart();
    const items = cart.map(i => {
        const p = allProducts.find(prod => String(prod.ProductID) === String(i.ProductID));
        return { ProductName: p.ProductName, quantity: i.quantity };
    });

    try {
        const res = await fetch("http://127.0.0.1:8000/api/recommend-with-cart", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ customer_id: user ? user.id : 0, cart: items })
        });
        const data = await res.json();
        window.lastBackendDiscount = data.discount || 0;

        container.innerHTML = "";
        data.recommended_products.forEach(name => {
            const product = allProducts.find(p => p.ProductName === name);
            if (!product) return;
            const card = document.createElement("div");
            card.className = "product-card";
            card.innerHTML = `
                <img src="Pictures/${product.Image}" class="product-img">
                <div class="product-info">
                    <div class="product-name">${product.ProductName}</div>
                    <div class="product-weight">${product.Weight || ""}</div>
                    <div class="product-price">Rs. ${product.Price}</div>
                    <button class="add-to-cart btn">Add to Cart</button>
                </div>
            `;
            card.querySelector(".add-to-cart").onclick = (e) => { e.stopPropagation(); addToCart(product); };
            card.onclick = () => { window.location.href = `product.html?id=${product.ProductID}`; };
            container.appendChild(card);
        });

        renderCart();
    } catch (err) {
        container.innerHTML = "<p>Failed to load recommendations.</p>";
        console.error(err);
    }
}

function renderCart() {
    const container = document.getElementById("cartContainer");
    if (!container) return;

    const cart = getCart();
    container.innerHTML = "";

    if (cart.length === 0) {
        container.innerHTML = "<p class='empty-cart'>Your cart is empty.</p>";
        const totalElem = document.getElementById("cartTotal")?.querySelector(".total");
        if (totalElem) totalElem.innerHTML = "Total: Rs. 0";
        window.lastBackendDiscount = 0;
        return;
    }

    let total = 0;
    cart.forEach(item => {
        const product = allProducts.find(p => String(p.ProductID) === String(item.ProductID));
        if (!product) return;

        const itemTotal = product.Price * item.quantity;
        total += itemTotal;

        const card = document.createElement("div");
        card.className = "cart-item";
        card.innerHTML = `
            <img src="Pictures/${product.Image}" class="cart-img">
            <div class="cart-item-info">
                <div class="name">${product.ProductName}</div>
                <div class="price">Rs. ${product.Price}</div>
                <div class="cart-item-quantity">
                    <button class="dec-btn">-</button>
                    <span>${item.quantity}</span>
                    <button class="inc-btn">+</button>
                </div>
            </div>
            <div class="cart-item-actions">
                <button class="remove-btn"><i class="fas fa-trash"></i></button>
                <div class="cart-item-total">Rs. ${itemTotal}</div>
            </div>
        `;

        card.querySelector(".inc-btn").onclick = () => { item.quantity++; saveCart(cart); };
        card.querySelector(".dec-btn").onclick = () => { if (item.quantity > 1) item.quantity--; saveCart(cart); };
        card.querySelector(".remove-btn").onclick = () => { cart.splice(cart.indexOf(item), 1); saveCart(cart); };

        container.appendChild(card);
    });

    const totalElem = document.getElementById("cartTotal")?.querySelector(".total");
    if (totalElem) {
        const user = getLoggedInUser();
        let discount = window.lastBackendDiscount || 0;

        // Only apply discount if >0
        const discountedTotal = total * (1 - discount);
        totalElem.innerHTML = `Total: Rs. ${total.toFixed(2)}${discount > 0 ? `<br>After Discount: Rs. ${discountedTotal.toFixed(2)}` : ""}`;
    }
}



async function doCheckout() {
    const cart = getCart();
    if (cart.length === 0) { alert("Cart empty!"); return; }

    const user = getLoggedInUser();
    if (!user) { alert("Login required!"); window.location.href = "login.html"; return; }

    const items = cart.map(i => {
        const p = allProducts.find(prod => String(prod.ProductID) === String(i.ProductID));
        return { ProductName: p.ProductName, quantity: i.quantity };
    });

    const total = cart.reduce((sum, i) => {
        const p = allProducts.find(prod => String(prod.ProductID) === String(i.ProductID));
        return sum + p.Price * i.quantity;
    }, 0);

    const name = document.getElementById("name")?.value || "";
    const phone = document.getElementById("phone")?.value || "";
    const city = document.getElementById("city")?.value || "";
    const address = document.getElementById("address")?.value || "";

    try {
        const res = await fetch("http://127.0.0.1:8000/api/checkout", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({
                user_id: user.id,
                items,
                total,
                shipping: { name, phone, city, address }
            })
        });

        const data = await res.json();
        if (!res.ok) throw new Error(data.detail || "Checkout failed");
        const discount = data.discount || 0;
        const discountedTotal = total * (1 - discount);

        localStorage.setItem("lastTransaction", JSON.stringify({
            transaction_id: data.transaction_id,
            total: total.toFixed(2),
            discountedTotal: discountedTotal.toFixed(2),
            discount: discount
        }));

        window.lastBackendDiscount = 0;
        localStorage.removeItem("cart");
        updateCartCount();
        renderCart();

        window.location.href = "checkout_success.html";

    } catch (err) {
        alert(err.message);
        console.error("Checkout error:", err);
    }
}


function prefillCheckoutForm() {
    const user = getLoggedInUser();
    if (!user) { alert("Login required!"); window.location.href = "login.html"; return; }
}

document.addEventListener("DOMContentLoaded", () => {
    currentUser = getLoggedInUser();
    updateHeaderUser();
    initPage();

    const checkoutBtn = document.getElementById("checkoutBtn");
    if (checkoutBtn) checkoutBtn.onclick = async () => { await doCheckout(); };

    const checkoutTitle = document.getElementById("checkoutTitle");
    if (checkoutTitle) {
        const lastTxn = JSON.parse(localStorage.getItem("lastTransaction") || "{}");
        if (lastTxn.transaction_id) {
            document.getElementById("transactionID").innerText = `Transaction ID: ${lastTxn.transaction_id}`;
            document.getElementById("totalAmount").innerText = `Total: Rs. ${lastTxn.total}`;
            document.getElementById("discountedAmount").innerText = `After Discount: Rs. ${lastTxn.discountedTotal}`;
            document.getElementById("discountMessage").innerText = lastTxn.discount > 0 ?
                `🎉 You saved ${(lastTxn.discount * 100).toFixed(0)}%!` : "";
        }
        const backBtn = document.getElementById("backHomeBtn");
        if (backBtn) backBtn.onclick = () => { window.location.href = "index.html"; };
    }
});
