
  document.getElementById("btn").onclick=function()
   {
    const firstName = document.querySelector('input[placeholder="Enter your First name"]').value.trim();
    const lastName = document.querySelector('input[placeholder="Enter your Last name"]').value.trim();
    const email = document.querySelector('input[placeholder="abc@gmail.com"]').value.trim();
    const password = document.querySelector('input[placeholder="Enter your password"]').value.trim();
    const confirmPassword = document.querySelector('input[placeholder="Confirm your password"]').value.trim();
    const country = document.getElementById("country").value.trim();
    const address = document.querySelector('input[placeholder="Enter your address"]').value.trim();
    const about = document.getElementById("about").value.trim();

    if (!firstName || !lastName || !email || !password || !confirmPassword ||
      !country || !address || !about) 
      {
      alert("Please fill in all fields.");
      return;
      }
    if (!email.endsWith("@gmail.com") || !email.includes("@")) 
    {
      alert("Email must be a valid Gmail address (e.g. abc@gmail.com).");
      return;
    }
    if (password.length !== 8) 
    {
      alert("Password must be of 8 characters.");
      return;
    }
    if (password !== confirmPassword) 
    {
      alert("Passwords do not match.");
      return;
    }
    alert("Form submitted successfully!");
  };

