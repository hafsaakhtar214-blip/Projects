function createRipple(e) {
  const button = e.currentTarget;
  const ripple = document.createElement("span");
  ripple.classList.add("ripple");

  const size = Math.max(button.clientWidth, button.clientHeight);
  ripple.style.width = ripple.style.height = size + "px";

  const rect = button.getBoundingClientRect();
  ripple.style.left = e.clientX - rect.left - size / 2 + "px";
  ripple.style.top = e.clientY - rect.top - size / 2 + "px";

  button.appendChild(ripple);
  ripple.addEventListener("animationend", () => ripple.remove());
}

async function loadProductPage() {
  const params = new URLSearchParams(window.location.search);
  const id = params.get("id");
  if (!id) return;

  const imgElem = document.getElementById("mainImage");
  const nameElem = document.getElementById("prodName");
  const priceElem = document.getElementById("prodPrice");
  const descElem = document.getElementById("prodDesc");
  const btnElem = document.getElementById("addToCartBtn");
  if (!imgElem || !nameElem || !priceElem || !descElem || !btnElem) return;

  try {
    const res = await fetch(`http://localhost:8080/api/products/${id}`);
    if (!res.ok) throw new Error("Failed to fetch product: " + res.status);
    const p = await res.json();

    imgElem.src = `/Pictures/${p.image?.trim() || 'placeholder.png'}`;
    nameElem.innerText = p.name || "Unnamed Product";
    priceElem.innerText = `${p.price || 0} PKR`;

    let html = `<p>${p.description || ""}</p>`;
    let pieces = 1;
    if (p.name?.includes("3PC")) pieces = 3;
    else if (p.name?.includes("2PC")) pieces = 2;

    if (pieces === 3) html += `<h3>Product Detail:</h3><p>3-piece set: Shirt, Dupatta, Trousers</p>`;
    else if (pieces === 2) html += `<h3>Product Detail:</h3><p>2-piece set: Shirt, Dupatta</p>`;
    else html += `<h3>Product Detail:</h3><p>Single-piece product: Shirt</p>`;

    html += `<p><strong>Stitch Type:</strong> ${p.stitchType || "N/A"}</p>`;

    if (p.stitchType && p.stitchType.toLowerCase() === "stitched") {
      html += `
        <label for="sizeSelect"><strong>Select Size:</strong></label>
        <select id="sizeSelect">
          <option value="S">Small</option>
          <option value="M">Medium</option>
          <option value="L">Large</option>
        </select>
      `;
    }

    descElem.innerHTML = html;

    btnElem.onclick = (e) => {
      createRipple(e);
      const sizeSelect = document.getElementById("sizeSelect");
      const selectedSize = sizeSelect ? sizeSelect.value : null;
      addToCart(p, selectedSize);
    };
  } catch (err) {
    console.error(err);
    descElem.innerHTML = `<p>Error loading product: ${err.message}</p>`;
  }
}

async function loadCollectionPage(category = "Women", piecesFilter = "All", stitchTypeFilter = "All") {
  const grid = document.getElementById("productGrid");
  if (!grid) return;

  const titleElem = document.getElementById("collection-title");
  if (titleElem) titleElem.innerText = `${category} Collection`;

  const categoryMap = { Women: 1, Men: 2, Kids: 3 };
  const categoryId = categoryMap[category] || 1;

  const filterPanel = document.getElementById("filterPanel");
  if (filterPanel) {
    filterPanel.style.display = (category === "Women") ? "block" : "none";
  }

  try {
    const res = await fetch(`http://localhost:8080/api/products/filter?categoryId=${categoryId}`);
    if (!res.ok) throw new Error("Failed to fetch products: " + res.status);
    let products = await res.json();

    if (!products || products.length === 0) {
      grid.innerHTML = "<p>No products found</p>";
      return;
    }

    if (piecesFilter !== "All") {
      products = products.filter(p => {
        if (piecesFilter === "1") return p.name?.includes("1PC");
        if (piecesFilter === "2") return p.name?.includes("2PC");
        if (piecesFilter === "3") return p.name?.includes("3PC");
        return false;
      });
    }

    if (stitchTypeFilter !== "All") {
      products = products.filter(p => p.stitchType?.toLowerCase() === stitchTypeFilter.toLowerCase());
    }

    grid.innerHTML = "";
    products.forEach(p => {
      const card = document.createElement("div");
      card.className = "product-card";
      card.innerHTML = `
        <img src="/Pictures/${p.image?.trim() || 'placeholder.png'}" alt="${p.name || ''}" />
        <h3>${p.name || 'Unnamed'}</h3>
        <p>${p.price || 0} PKR</p>
        <button class="add-to-cart-btn">Add to Cart</button>
      `;
      card.querySelector(".add-to-cart-btn").onclick = (e) => {
        e.stopPropagation();
        createRipple(e);
        addToCart(p, null);
      };
      card.onclick = () => window.location.href = `product.html?id=${p.id}`;
      grid.appendChild(card);
    });
  } catch (err) {
    console.error(err);
    grid.innerHTML = `<p>Error loading products: ${err.message}</p>`;
  }
}

function setupCollectionPage() {
  const params = new URLSearchParams(window.location.search);
  let category = params.get("category") || "Women";
  let stitchType = params.get("stitchType") || "All";
  let pieces = params.get("pieces") || "All";

  const filterBtns = document.querySelectorAll(".filter-btn");

  document.querySelectorAll(".category-btn").forEach(btn => {
    btn.onclick = () => {
      category = btn.dataset.category;
      loadCollectionPage(category, pieces, stitchType);

      document.querySelectorAll(".category-btn").forEach(b => b.classList.remove("active"));
      btn.classList.add("active");
    };
  });

  filterBtns.forEach(btn => {
    btn.onclick = () => {
      const btnStitch = btn.dataset.stitch;
      const btnPieces = btn.dataset.pieces;

      if (btnStitch) stitchType = btnStitch;
      if (btnPieces) pieces = btnPieces;

      loadCollectionPage(category, pieces, stitchType);

      filterBtns.forEach(b => b.classList.remove("active"));
      btn.classList.add("active");
    };
  });

  loadCollectionPage(category, pieces, stitchType);
}

function addToCart(product, size = null) {
  let cart = JSON.parse(localStorage.getItem("cart")) || [];
  const existing = cart.find(i => i.id === product.id && i.size === size);
  if (existing) existing.quantity++;
  else cart.push({ ...product, quantity: 1, size });
  localStorage.setItem("cart", JSON.stringify(cart));
  alert("Added to cart 🛒");
}

function loadCart() {
  const cart = JSON.parse(localStorage.getItem("cart")) || [];
  const container = document.getElementById("cartContainer");
  if (!container) return;
  container.innerHTML = "";

  if (cart.length === 0) {
    container.innerHTML = "<p>Your cart is empty</p>";
    const summary = document.getElementById("cartSummary");
    if (summary) summary.innerHTML = "";
    return;
  }

  let total = 0;
  cart.forEach((item, index) => {
    total += item.price * item.quantity;
    const div = document.createElement("div");
    div.className = "cart-item";
    div.innerHTML = `
      <img src="/Pictures/${item.image?.trim() || 'placeholder.png'}" alt="${item.name || ''}">
      <div class="cart-info">
        <h3>${item.name || 'Unnamed'}</h3>
        ${item.size ? `<p>Size: ${item.size}</p>` : ""}
        <p>Price: ${item.price || 0} PKR</p>
        <div class="cart-actions">
          <button class="btn qty-btn" data-index="${index}" data-action="decrease">-</button>
          <span>${item.quantity}</span>
          <button class="btn qty-btn" data-index="${index}" data-action="increase">+</button>
          <button class="btn remove-btn" data-index="${index}">Remove</button>
        </div>
      </div>
    `;
    container.appendChild(div);
  });

  const summary = document.getElementById("cartSummary");
  if (summary) summary.innerHTML = `<h2>Total: ${total} PKR</h2>`;
  attachCartEvents();
}

function attachCartEvents() {
  const cart = JSON.parse(localStorage.getItem("cart")) || [];
  document.querySelectorAll(".qty-btn").forEach(btn => {
    btn.onclick = (e) => {
      createRipple(e);
      const index = btn.dataset.index;
      const action = btn.dataset.action;
      if (action === "increase") cart[index].quantity++;
      else if (action === "decrease" && cart[index].quantity > 1) cart[index].quantity--;
      localStorage.setItem("cart", JSON.stringify(cart));
      loadCart();
    };
  });

  document.querySelectorAll(".remove-btn").forEach(btn => {
    btn.onclick = (e) => {
      createRipple(e);
      const index = btn.dataset.index;
      cart.splice(index, 1);
      localStorage.setItem("cart", JSON.stringify(cart));
      loadCart();
    };
  });
}

async function login(email, password) {
  try {
    const res = await fetch("http://localhost:8080/api/auth/login", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ email, password })
    });
    if (res.ok) {
      const user = await res.json();
      localStorage.setItem("userId", user.userId || user.id);
      localStorage.setItem("userName", user.name || email.split("@")[0]);
      updateHeaderUser();
      window.location.href = "index.html";
    } else if (res.status === 404) alert("User not found!");
    else alert("Wrong password");
  } catch (err) {
    console.error(err);
    alert("Login failed: " + err.message);
  }
}

async function signup(email, password) {
  try {
    const res = await fetch("http://localhost:8080/api/auth/signup", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ email, password })
    });
    if (res.ok) {
      const user = await res.json();
      localStorage.setItem("userId", user.userId || user.id);
      localStorage.setItem("userName", user.name || email.split("@")[0]);
      updateHeaderUser();
      window.location.href = "index.html";
    } else if (res.status === 409) alert("User already exists!");
    else alert("Signup failed");
  } catch (err) {
    console.error(err);
    alert("Signup failed: " + err.message);
  }
}

function updateHeaderUser() {
  const userName = localStorage.getItem("userName");
  const headerRight = document.querySelector(".header-right");
  if (!headerRight) return;

  headerRight.innerHTML = `
    <a href="cart.html" class="header-icon"><i class="fas fa-shopping-cart"></i></a>
  `;

  if (userName) {
    const userDiv = document.createElement("div");
    userDiv.className = "header-user-dropdown";
    userDiv.innerHTML = `
      <button id="userNameBtn">${userName} <i class="fas fa-caret-down"></i></button>
      <div id="userDropdown" class="user-dropdown-content">
        <button id="logoutBtn">Logout</button>
      </div>
    `;
    headerRight.appendChild(userDiv);

    const userBtn = document.getElementById("userNameBtn");
    const dropdown = document.getElementById("userDropdown");
    const logoutBtn = document.getElementById("logoutBtn");

    userBtn.onclick = () => dropdown.classList.toggle("active");
    logoutBtn.onclick = () => {
      localStorage.removeItem("userId");
      localStorage.removeItem("userName");
      updateHeaderUser();
    };
  } else {
    const loginLink = document.createElement("a");
    loginLink.href = "login.html";
    loginLink.className = "header-icon";
    loginLink.innerHTML = `<i class="fas fa-user"></i>`;
    headerRight.appendChild(loginLink);
  }
}

function setupCheckout() {
  const checkoutForm = document.getElementById("checkoutForm");
  if (!checkoutForm) return;

  checkoutForm.onsubmit = async (e) => {
    e.preventDefault();
    const userId = localStorage.getItem("userId");
    if (!userId) return alert("Please login first!");

    const cart = JSON.parse(localStorage.getItem("cart")) || [];
    if (!cart.length) return alert("Cart is empty!");

    const name = document.getElementById("name").value.trim();
    const phone = document.getElementById("phone").value.trim();
    const address = document.getElementById("address").value.trim();
    const city = document.getElementById("city").value.trim();

    if (!name || !phone || !address || !city) return alert("Please fill all the fields!");

    const totalAmount = cart.reduce((sum, i) => sum + i.price * i.quantity, 0);

    try {
      const res = await fetch("http://localhost:8080/api/orders", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ userId, totalAmount, name, phone, address, city, items: cart })
      });

      if (res.ok) {
        alert("Order placed successfully!");
        localStorage.removeItem("cart");
        window.location.href = "index.html";
      } else throw new Error("Failed to place order");
    } catch (err) {
      console.error(err);
      alert(err.message);
    }
  };
}

document.addEventListener("DOMContentLoaded", () => {
  updateHeaderUser();
  setupCollectionPage();
  loadProductPage();
  loadCart();
  setupCheckout();

  const loginBtn = document.getElementById("enterb");
  if (loginBtn) loginBtn.onclick = async (e) => {
    createRipple(e);
    const inputs = document.querySelectorAll("#signmenu input");
    const email = inputs[0].value.trim();
    const password = inputs[1].value.trim();
    if (!email || !password) return alert("Fill in all fields");
    await login(email, password);
  };

  const signupBtn = document.getElementById("submitb");
  if (signupBtn) signupBtn.onclick = async (e) => {
    createRipple(e);
    const inputs = document.querySelectorAll("#signupmenu input");
    const email = inputs[0].value.trim();
    const password = inputs[1].value.trim();
    const confirmPassword = inputs[2].value.trim();
    if (!email || !password || !confirmPassword) return alert("Fill in all fields");
    if (password !== confirmPassword) return alert("Passwords do not match");
    await signup(email, password);
  };
});
